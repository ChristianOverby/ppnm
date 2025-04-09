import numpy as np
from scipy.integrate import quad

print("---------------------------------------------------------------------------------")
print("Pyhton comparison")

# functions
def sqrt_inv(x) :
    return 1/np.sqrt(x)

def ln_sqrt(x) :
    return np.log(x)/np.sqrt(x)

def square_inv(x) : 
    return 1.0 / (1.0 + x * x)

def lorentzian(x) :
    return 1.0 / (x * x + 0.01)

val, err = quad(sqrt_inv, 0, 1)
evals = quad(sqrt_inv, 0, 1, full_output=1)[2]['neval']

print(f"integration of ∫_0^1 dx 1/√(x) = {val}    err: {err}      evals: {evals}")

val, err = quad(ln_sqrt, 0, 1)
evals = quad(ln_sqrt, 0, 1, full_output=1)[2]['neval']

print(f"integration of ∫_0^1 dx ln(x)/√(x) = {val}    err: {err}      evals: {evals}")

val, err = quad(square_inv, -np.inf, np.inf)
evals = quad(square_inv, -np.inf, np.inf, full_output=1)[2]['neval']

print(f"integration of Inverse square ∫_inf^inf 1 / (1 + x^2) = {val}    err: {err}      evals: {evals}")

val, err = quad(lorentzian, -np.inf, np.inf)
evals = quad(lorentzian, -np.inf, np.inf, full_output=1)[2]['neval']

print(f"integration of Lorentzian ∫_-inf^inf 1 / (x^2 + 0.01) = {val}    err: {err}      evals: {evals}")

print("Probably using CC on the infinite function conversion would help reduce the number evals \nHowever the scipy implementation is much more efficient than mine :(")
