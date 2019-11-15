import pandas as pd
import numpy as np
import json

with open("AHU06 Heating Coil.json") as f:
    data = json.load(f)

print(data[0])
