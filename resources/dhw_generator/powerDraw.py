import numpy as np
import pandas as pd
import enum
import datetime

TIME_FORMAT = '%Y-%m-%d %H:%M:%S'
KG_PER_GALLON = 3.7854
SPECIFIC_HEAT_H2O = 4190
JOULE_PER_WATT_HOUR = 3600

def load_data(filepath: str) -> pd.DataFrame:
    data = pd.read_csv(filepath)
    if data.isnull().values.any():
        print('data is missing values')
        exit()
    return data

def toTimeSeries(data:pd.DataFrame) -> pd.DataFrame:
    data['start_time'] = pd.to_datetime(data['start_time'],format=TIME_FORMAT)
    data['end_time'] = pd.to_datetime(data['end_time'], format=TIME_FORMAT)
    return data

def to_celsius(fahrenheit: float) -> float:
    return (fahrenheit - 32)/1.8

def to_fahrenheit(celsius: float) -> float:
    return celsius*1.8 + 32

def to_kilograms(gallons: float) -> float:
    return KG_PER_GALLON*gallons

def heating_energy(temp_2: float, temp_1: float, volume: float) -> float:
    c = SPECIFIC_HEAT_H2O
    m = to_kilograms(volume)
    t2 = to_celsius(temp_2)
    t1 = to_celsius(temp_1)
    return c*m*(t2-t1)/JOULE_PER_WATT_HOUR

def temp_change(temp: float, volume: float, energy: float) -> float:
    c = SPECIFIC_HEAT_H2O
    m = to_kilograms(volume)
    t1 = to_celsius(temp)
    t2 = (energy*JOULE_PER_WATT_HOUR)/(c*m) + t1
    return to_fahrenheit(t2)

def tank_temp(t1: float, m1: float, t2: float, m2: float) -> float:
    """internal energy balance
    """
    return (m1*t1 + m2*t2)/(m1+m2)

def ambient_loss(temp: float) -> float:
    """TODO
    """        
    return temp - temp/1000000

class State(enum.Enum):
    """TODO Ref: EPRI 2045 Perfromance Results Table-2
    """
    NORMAL = 1
    SHED = 2
    END_SHED = 3
    LOAD_UP = 4
    CRITICAL_PEAK = 5

class WaterHeater():
    """Electric Water Heater Simulator
    """ 
       
    on = False
    state = State.NORMAL
    
    def __init__(self, volume, temp_setpoint, event_profile: pd.DataFrame) -> None:
        self.VOLUME = volume
        self.TEMP_SETPOINT = temp_setpoint
        self.EVENTS = toTimeSeries(event_profile)
        self.TEMP_INLET = 50
        self.POWER = 4500
        self.load_profile()
        
    def load_profile(self) -> None:
        timestamps = pd.date_range(self.EVENTS['start_time'][0], self.EVENTS['start_time'][len(self.EVENTS)-1], freq='S')
        draw = np.zeros(len(timestamps), dtype=float)
        temp = np.ones(len(timestamps), dtype=float)*self.TEMP_SETPOINT
        energy = np.zeros(len(timestamps), dtype=float)
        power = np.zeros(len(timestamps), dtype=float)
        self.data = pd.DataFrame({'draw': draw, 'temp':temp, 'energy':energy, 'power':power}, index=timestamps)
            
    def run(self) -> None:
        N = len(self.EVENTS)-1
        event_idx = 0
        last_temp = self.TEMP_SETPOINT
        for  idx, row in self.data.iterrows():
            start = self.EVENTS['start_time'][event_idx]
            end = self.EVENTS['end_time'][event_idx]
            if idx <= end and idx >= start:
                row.draw = self.EVENTS['draw'][event_idx]
                row.temp = tank_temp(last_temp, self.VOLUME-row.draw, self.TEMP_INLET, row.draw)
                last_temp = row.temp
                row.energy = heating_energy(self.TEMP_SETPOINT, row.temp, self.VOLUME)
                print(idx, row.draw, last_temp)
            else:
                if idx > end and event_idx < N:
                    event_idx+=1
                    
            if (last_temp <= self.TEMP_SETPOINT - 2):
                self.on = True
            elif (last_temp > self.TEMP_SETPOINT + 2):
                self.on = False
                
            if self.on:
                row.power = self.POWER
                watt_sec = self.POWER/(60*60)
                row.temp = temp_change(last_temp, self.VOLUME, watt_sec)
                last_temp = row.temp
                row.energy = heating_energy(self.TEMP_SETPOINT, row.temp, self.VOLUME)
                
            row.temp = ambient_loss(last_temp)
            last_temp = row.temp
                
        self.data.to_csv(f'outputs/water-sim.csv',index_label='timestamp')
            
if __name__ == '__main__':
    name = 'std-1br-dwh'
    profile = load_data(f'outputs/{name}-30.csv')  
    WaterHeater(80, 120, profile).run()
    