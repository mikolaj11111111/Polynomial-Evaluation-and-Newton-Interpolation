# Polynomial Evaluation and Newton Interpolation

## Description
Compares polynomial evaluation methods and implements Newton interpolation with divided differences. Analyzes computational efficiency and interpolation accuracy.

## Features
- **Natural Form Polynomial** - Standard a₀ + a₁x + a₂x² + ... evaluation
- **Horner's Method** - Efficient polynomial evaluation algorithm
- **Newton Interpolation** - Using divided differences for interpolation
- **Performance Comparison** - Timing analysis between methods
- **Optimal Node Analysis** - Finds best number of interpolation nodes

## Mathematical Background
- **Horner's Method**: Reduces polynomial evaluation from O(n²) to O(n)
- **Newton Form**: P(x) = a₀ + a₁(x-x₀) + a₂(x-x₀)(x-x₁) + ...
- **Divided Differences**: Recursive computation of interpolation coefficients

## Usage
Requires two input files:
- `interpolacja_H_gr_01.txt` - Polynomial coefficients and x values
- `interpolacja_N_gr_01.txt` - Interpolation data (xi and f(xi) values)

Program compares polynomial evaluation methods and performs Newton interpolation analysis.
