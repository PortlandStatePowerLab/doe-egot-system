import numpy as np
import pandas as pd
import datetime
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

TIME_FORMAT = '%m/%d %I:%M:%S %p'

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

if __name__ == '__main__':
    #base_names = ['std-1br-dwh','std-2br-dwh','std-3br-dwh','std-4br-dwh','std-5br-dwh']
    base_names = ['std-1br-dwh']
    for name in base_names:
        raw = loadData(f'data/{name}.csv')
        data = toTimeSeries(raw)
        
        cnt = 1
        for idx, day in data.groupby(data.Time.dt.date):
                day.to_csv(f'data/daily/{name}-{idx}.csv', index=False)