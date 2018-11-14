#pragma once
#ifndef RATIONALFRACTION_H_INCLUDED
#define RATIONALFRACTION_H_INCLUDED

class RationalFraction {
    private:
        RationalFraction* reduce();

    public:
        int numerator;
        int denominator;

        RationalFraction();
        RationalFraction(const RationalFraction& rf);
        RationalFraction(int numerator, int denominator);
        int getDenominator();
        RationalFraction* setDenominator(int denominator);
        int getNumerator();
        RationalFraction* setNumerator(int numerator);
        RationalFraction* operator+=(const RationalFraction& rf);
        RationalFraction* operator*=(const RationalFraction& rf);
        RationalFraction* operator/=(const RationalFraction& rf);
        int compare(const RationalFraction& rf);
        void print();
};


#endif // RATIONALFRACTION_H_INCLUDED
