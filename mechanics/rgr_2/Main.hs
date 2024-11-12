module Main (main, _M, phi_1, phi_2, phi_3, tau_1, tau_2, tau_3) where

phi_c = 2e-2

_D = 50e-3
_G = 0.8e11
_L = 1.2

_M :: Double
_M = phi_c * pi * _D^4 * _G /
        (_L * (64.0 * 8.5 / 1.5^4 + 32 * 7 / 1.25^4 + 32 * 3 / 1.75^4))

phi_1, phi_2, phi_3 :: Double
phi_1 = - 64 * 8.5 * _M * _L / ( pi * _D^4 * _G * 1.5^4)
phi_2 = phi_1 - 32 * 7 * _M * _L / ( pi * _D^4 * _G * 1.25^4)
phi_3 = phi_2 - 32 * 3 * _M * _L / ( pi * _D^4 * _G * 1.75^4)

_Wp_1 = pi * 1.5^3 * _D^3 / 16
_Wp_2 = pi * 1.25^3 * _D^3 / 16
_Wp_3 = pi * 1.75^3 * _D^3 / 16

tau_1, tau_2, tau_3 :: Double
tau_1 = 8.5 * _M / _Wp_1
tau_2 = 7 * _M / _Wp_2
tau_3 = 3 * _M / _Wp_3

main :: IO ()
main = putStrLn "Calc..."
