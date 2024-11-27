import numpy as np
import pandas as pd
import datetime
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

TIME_FORMAT = '%m/%d %I:%M:%S %p'

class Event():
    def __init__(self, start, end, draw):
        self.start_time = start
        self.end_time = end
        self.water_draw = draw
        
    def __repr__(self) -> str:
        return f"start:{self.start_time}, end: {self.end_time}, draw: {self.water_draw}"

def loadData(filepath: str) -> pd.DataFrame:
    data = pd.read_csv(filepath)
    if data.isnull().values.any():
        print('data is missing values')
        exit()
    return data

def toTimeSeries(data:pd.DataFrame) -> pd.DataFrame:
    data['Time'] = pd.to_datetime(data['Time'],format=TIME_FORMAT)
    data['Duration'] = pd.to_timedelta(data['Duration'], unit='s')
    return data

def sliceMonth(data:pd.DataFrame, month:int) -> pd.DataFrame:
    mask = (data['Time'].dt.month == month)
    return data.loc[mask]
        
def toEvents(data:pd.DataFrame) -> np.ndarray:
    n = len(data)
    events = np.empty(n, dtype=Event)
    for idx, row in data.iterrows():
        start = row['Time']
        end = start + row['Duration']
        draw = row['Hot']/60
        events[idx] = Event(start, end, draw)
    return events

def stackEvents(events:np.ndarray) -> pd.DataFrame:
    timestamps = pd.date_range(events[0].start_time, events[-1].end_time, freq='S')
    draws = np.empty(len(timestamps), dtype=float)
    data = pd.DataFrame({'timestamps': timestamps, 'draws': draws})
    print(data)
    
    for event in events:
        mask = (data['timestamps'] > event.start_time) & (data['timestamps'] < event.end_time)
        data.loc[mask, 'draws'] += event.water_draw
            
    return data
    
def groupTimeSeries(data:pd.DataFrame) -> pd.DataFrame:
    data['H'] = data.timestamps.dt.hour
    data['M'] = data.timestamps.dt.minute
    data['S'] = data.timestamps.dt.second
    return data.groupby(['H', 'M', 'S']).draws.mean()

if __name__ == '__main__':
    base_names = ['std-1br-dwh','std-2br-dwh','std-3br-dwh','std-4br-dwh','std-5br-dwh']
    month = 1
    for name in base_names:
        raw = loadData(f'data/{name}.csv')
        data = toTimeSeries(raw)
        data = sliceMonth(data, month)
        events = toEvents(data)
        stacked = stackEvents(events)
        grouped = groupTimeSeries(stacked)
        grouped.to_csv(f'outputs/grouped-{name}-{month}.csv')