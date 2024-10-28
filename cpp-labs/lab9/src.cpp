#include "lab9.hpp"
#include <codecvt>
#include <iostream>
#include <stdexcept>

namespace lab9 {
    /*
     * Sub set of exception throwed by math operations.
     */
    struct MathException: public std::runtime_error {
        MathException(const std::string &content):
            std::runtime_error("Math: " + content) {}
    };

    /*
     * Exception throw by division by zero.
     */
    struct DivideByZeroException: public MathException {
        /*
         * Construct exception.
         *
         * @param domen (by default is "Number") domen in division by zero
         * happens.
         */
        DivideByZeroException(std::string domen = "Numbers"):
            MathException("Divide by zero. [domen: " + domen + "]") {} 
    };

    /*
     * Complex Number. Contains real and imaginary parts.
     */
    struct Complex {
        double real, imag;

        Complex(): real{0}, imag{0} { }
        Complex(double real, double imag): real{real}, imag{imag} { }

        [[nodiscard("Pur function; changes nothing.")]]
        /**
         * Checks if complex number is zero.
         *
         * @return if number is zero.
         */
        constexpr bool isZero(void) const noexcept { return real == 0 && imag == 0; }

        [[nodiscard("use return value")]]
        /*
         * Display only meaningfull information about number.
         *
         * - ```Complex{0, 0}``` => "0".
         * - ```Complex{23.5, 0}``` => "23.5".
         * - ```Complex{0, 23.5}``` => "23.5j".
         * - ```Complex{13.4, 23.5}``` => "13.4 + 23.5j".
         */
        std::string displayCosmetic(void) const noexcept {
            if (isZero()) return "0";
            if (real == 0) return std::to_string(imag) + "j";
            if (imag == 0) return std::to_string(real);

            return std::to_string(real) + " + " + std::to_string(imag) + "j";
        }
    };
    /*
     * Helper function to create complex numbers in short way.
     */
    Complex cn(double rl, double im) {
        return Complex { rl, im };
    }
    /*
     * Display complex number to the stream.
     */
    std::ostream& operator<<(std::ostream& os, const Complex& cn) {
        return os << cn.real << "+" << cn.imag << "j";
    }

    /*
     * Addition of complex numbers.
     * 
     * @param fst, snd -- complex numbers to add.
     * @return result of addition. (fst + snd)
     */
    Complex operator+(const Complex& fst, const Complex& snd) {
        return { fst.real + snd.real, fst.imag + snd.imag };
    }

    /*
     * Assigned addition of complex numbers
     *
     * @param self -- complex number to assign.
     * @param delata -- value to add.
     */
    void operator+=(Complex& self, const Complex& delta)  {
        self.real += delta.real;
        self.imag += delta.imag;
    }

    /*
     * Substraction of complex numbers.
     * 
     * @param fst, snd -- complex numbers to substract.
     * @return result of substraction. (fst - snd)
     */
    Complex operator-(const Complex& fst, const Complex& snd) {
        return { fst.real - snd.real, fst.imag - snd.imag };
    }

    /*
     * Assigned substraction of complex numbers
     *
     * @param self -- complex number to assign.
     * @param delata -- value to substract.
     */
    void operator-=(Complex& self, const Complex& delta)  {
        self.real -= delta.real;
        self.imag -= delta.imag;
    }

    /*
     * Multiplication of complex numbers.
     *
     * @param fst, snd -- complex numbers to multiply.
     * @return result of multiplication. (fst * snd)
     */
    Complex operator*(const Complex& fst, const Complex& snd) {
        return { 
            fst.real * snd.real - fst.imag * snd.imag,
            fst.real * snd.imag - fst.imag * snd.real
        };
    }

    /*
     * Assigned multiplication of complex numbers.
     * 
     * @param self -- complex number to assign.
     * @param delata -- value to multiply.
     */
    void operator*=(Complex& self, const Complex& q) {
        self = self * q;
    }

    /*
     * Division of complex numbers.
     *
     * @param fst, snd -- complex numbers to divide.
     * @return result of division ( fst / snd )
     * 
     * @throw trhow DivideByZeroException when divide by zero complex (0 + 0j).
     */
    Complex operator/(const Complex& fst, const Complex& snd) {
        if (snd.isZero()) throw DivideByZeroException("Complex");

        return {
            (fst.real * snd.real + fst.imag * snd.imag)
                    / (snd.real * snd.real + snd.imag * snd.imag),
            (fst.imag * snd.real - fst.real * snd.imag)
            		/ (snd.real * snd.real + snd.imag * snd.imag)
        };
    }

    /*
     * Applyed division of complex numbers.
     *
     * @param fst, snd -- complex numbers to divide.
     * @return result of division ( fst / snd )
     *
     * @throw trhow DivideByZeroException when divide by zero complex (0 + 0j).
     */
    void operator/=(Complex& self, const Complex& divider) {
        self = self / divider;
    }

    /*
     * Equal operator for complex numbers.
     *
     * @param fst, snd -- numbers to compare.
     * @return result of comparing (fst == snd).
     */
    bool operator==(const Complex& fst, const Complex& snd) {
        return fst.real == snd.real && fst.imag == snd.imag;
    }


	class Equation {
        Complex _a, _b, _c;

        public:
            Equation(double a, double b, double c): _a{a, 0}, _b{b, 0}, _c{c, 0} { }
            Equation(Complex a, Complex b, Complex c): _a{a}, _b{b}, _c{c} { }

        friend std::ostream& operator<<(std::ostream& os, const Equation& equation);
	};
    std::ostream& operator<<(std::ostream& os, const Equation& equation) {
        bool is_prev = false;
        if (!equation._a.isZero()) {
            if (equation._a.real == 0 || equation._a.imag == 0)
                os << equation._a.displayCosmetic();
            else
                os << "(" << equation._a.displayCosmetic() << ")";

            os << " x^2";
            is_prev = true;
        }

        if (!equation._b.isZero()) {
            if (is_prev) os << " + ";

            if (equation._b.real == 0 || (equation._b.imag == 0 && equation._b.real > 0))
                os << equation._b.displayCosmetic();
            else
                os << "(" << equation._b.displayCosmetic() << ")";

            os << " x";
        }

        if (!equation._c.isZero()) {
            if (is_prev) os << " + ";
            os << equation._c.displayCosmetic();
        }

        os << " = 0";
        return os;
    }

	void runLab9(void) {
        std::cout << "Lab9" << std::endl;

        Equation eq_1 { {10, 1}, {20, 2}, {0, 4} };
        std::cout << eq_1 << std::endl;
	}
}
