module Second (q, _Q_y, _M_x) where


_W_x, sigma :: Double
_W_x = 480 * 0.01 * 0.01 * 0.01
sigma = 150 * 1000000
_L = 1.2

q :: Double
q = (_W_x * sigma) / (3 * _L)

_Q_y :: Double -> Double
_Q_y z
    | z < _L = -2.5 * _L * q
    | z >= _L && z < 3 * _L = q * _L
    | z >= 3 * _L = q * (z - 4 * _L)

_M_x :: Double -> Double
_M_x z
    | z < _L = q * _L * ( 3 * _L - 2.5 * z )
    | z >= _L && z < 3 * _L = q * _L * (z - 0.5 * _L)
    | z >= 3 * _L = q * (2 * _L^2 + _L * z - 0.5 * z^2)
