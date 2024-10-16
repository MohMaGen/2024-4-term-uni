module Second (_RAY, _RBX, _RBY, _MO, showall) where

_L :: Double
q1 :: Double
q2 :: Double
_P :: Double
pi2 :: Double
_RAY :: Double
_RBX :: Double
_RBY :: Double
_MO :: Double

_L = 1.5
q1 = 25
q2 = 12
_P = 30

pi2 = sqrt(0.5)

_RAY = -14.234
_RBX = 58.713
_RBY = - ( _RAY + 2.0 * q2 * _L + _P * pi2)
_MO = (- _RAY * _L) + (-0.5 * q1 * _L * _L)
        - 16.0 + (2.0 * _L * _P * pi2)
        + (2.0 * _L * _RBY) + (_L * _RBX)

showall :: (Double, Double, Double, Double)
showall = (_RAY, _RBX, _RBY, _MO)
