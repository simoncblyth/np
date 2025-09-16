
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import List
import numpy as np
import my_ext  # Your nanobind extension

app = FastAPI()

# Pydantic model for input/output
class ArrayInput(BaseModel):
    data: List[float]

class ArrayOutput(BaseModel):
    data: List[float]

@app.post("/process", response_model=ArrayOutput)
async def process_array(input: ArrayInput):
    try:
        # Convert input list to NumPy array
        input_array = np.array(input.data, dtype=np.float64)
        # Call nanobind function
        output_array = my_ext.process_array(input_array)
        # Convert output to list for JSON response
        return ArrayOutput(data=output_array.tolist())
    except Exception as e:
        raise HTTPException(status_code=400, detail=f"Error processing array: {str(e)}")


