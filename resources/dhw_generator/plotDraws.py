import numpy as np
import pandas as pd
import datetime
import matplotlib.pyplot as plt
import matplotlib.dates as md
from matplotlib.colors import ListedColormap

TIME_FORMAT = '%Y-%m-%d %H:%M:%S'

def loadData(filepath: str) -> pd.DataFrame:
    data = pd.read_csv(filepath)
    if data.isnull().values.any():
        print('data is missing values')
        exit()
    return data

def toTimeSeries(data:pd.DataFrame) -> pd.DataFrame:
    data['timestamp'] = pd.to_datetime(data['timestamp'],format=TIME_FORMAT)
    return data

if __name__ == '__main__':
    #base_names = ['std-1br-dwh','std-2br-dwh','std-3br-dwh','std-4br-dwh','std-5br-dwh']
    sim = loadData("outputs/water-sim.csv")
    sim = toTimeSeries(sim)
    
    fig, ax1 = plt.subplots()

    color = 'tab:red'
    
    # major locator
    xloc=md.HourLocator(interval = 1)
    ax1.xaxis.set_major_locator(xloc)

    # major formatter
    majorFmt = md.DateFormatter('%H')
    ax1.xaxis.set_major_formatter(majorFmt)

    ax1.set_xlabel('hour (HH)')
    ax1.set_ylabel('draw (gps)', color=color)
    ax1.plot(sim.timestamp, sim.draw, color=color)
    ax1.tick_params(axis='y', labelcolor=color)

    ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

    color = 'tab:blue'
    ax2.set_ylabel('temperature (F)', color=color)  # we already handled the x-label with ax1
    ax2.plot(sim.timestamp, sim.temp, color=color)
    ax2.tick_params(axis='y', labelcolor=color)
    plt.savefig(f'outputs/water-sim.png', bbox_inches='tight')