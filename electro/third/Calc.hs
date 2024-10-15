module Calc (_RC, _R2, _R4, _I1, _I2, _I3, _I4, p) where

_RC, _R2, _R4 :: [Double]
_RC = [ 110, 110, 110 ]
_R2 = [ 30, 80, 110 ]
_R4 = [ 30, 80, 110 ]

_I1, _I2, _I3, _I4 :: [Double]
_I1 = [ 2, 2, 2 ]
_I2 = [ 2.7, 7.33, 2 ]
_I3 = [ 2, 2, 2 ]
_I4 = [ 4.3, 3.4, 2.6 ]

p :: (Double, Double) -> Double
p (i, r) = i * i * r
