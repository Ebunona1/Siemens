import pandas as pd
import numpy as np
import json
import matplotlib.pyplot as plt

file_names = ["5s res sensor_id=BMS-L1O14S31&start=2017-03-20T00_00_00&end=2017-03-20T23_59_59.json",
                "5s res sensor_id=BMS-L1O14S32&start=2017-03-20T00_00_00&end=2017-03-20T23_59_59.json",
                "5s res sensor_id=BMS-L1O14S33&start=2017-03-20T00_00_00&end=2017-03-20T23_59_59.json",
                ]

with open("AHU06 Heating Coil.json") as f:
    data = json.load(f)

values = data["values"]

dtype = [("value", float), ("time", "S10")]
data_arr = []

for i in values:
    data_arr.append((float(i["value"]), i["time"]))

arr = np.array(data_arr, dtype=dtype)
np.sort(arr, order="time")

x = [i[1] for i in arr]
y = [j[0] for j in arr]

plt.plot(x, y)
plt.show()
print(data_arr)
