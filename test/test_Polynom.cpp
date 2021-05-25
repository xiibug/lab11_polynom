#include "Polynom.h"
#include "../gtest/gtest.h"

TEST(TMonom, can_create_monom)
{
	ASSERT_NO_THROW(TMonom a(new double[3]{ 1, 2, 3 }, 3, 1));
}

TEST(TMonom, can_copy_monom)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	ASSERT_NO_THROW(TMonom b(a));
}

TEST(TMonom, can_assign_monom)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	ASSERT_NO_THROW(TMonom b = a);
}

TEST(TMonom, can_compare_monom_operator_equally)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 1, 2, 3 }, 3, 1);
	EXPECT_EQ(a == b, true);
}

TEST(TMonom, can_compare_monom_operator_not_equally)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 1, 2, 3 }, 3, 1);
	EXPECT_EQ(a != b, false);
}

TEST(TMonom, can_get_K)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	EXPECT_EQ(a.GetK(), 1);
}

TEST(TMonom, can_set_K)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	a.SetK(4);
	EXPECT_EQ(a.GetK(), 4);
}

TEST(TMonom, can_get_dim)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	EXPECT_EQ(a.GetDim(), 3);
}

TEST(TMonom, can_set_dim)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	a.SetDim(10);
	EXPECT_EQ(a.GetDim(), 10);
}

TEST(TMonom, can_get_elem_data)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	EXPECT_EQ(a[0], 1);
}

TEST(TMonom, can_multiplicate)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
	TMonom c;
	ASSERT_NO_THROW(b * a);
}

TEST(TMonom, can_divide)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
	ASSERT_NO_THROW(a / b);
}

TEST(TMonom, can_add)
{
	TMonom a(new double[1]{ 3 }, 1, 1);
	TMonom b(new double[1]{ 1 }, 1, 1);
	TMonom* c;
	ASSERT_NO_THROW(c = a + b);
}

TEST(TMonom, can_subtract)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
	TMonom* c;
	ASSERT_NO_THROW(c = b - a);
}

TEST(TMonom, can_compare_more)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);

	EXPECT_EQ(a > b, false);
}

TEST(TMonom, can_compare_less)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);

	EXPECT_EQ(a < b, true);
}




TEST(Polynom, can_create_polynom)
{
	ASSERT_NO_THROW(TPolynomial P1);
}

TEST(Polynom, can_copy_polynom)
{
	TPolynomial P1;
	ASSERT_NO_THROW(TPolynomial P2(P1));
}

TEST(Polynom, can_operator_plus_equally)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TPolynomial P1;
	ASSERT_NO_THROW(P1 += a);
}

TEST(Polynom, can_multiplicate)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
	TPolynomial P1, P2, P3;
	P1 += a;
	P2 += b;

	ASSERT_NO_THROW(P1 * P2);
}

TEST(Polynom, can_add)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
	TPolynomial P1, P2;
	P1 += a;
	P2 += b;

	ASSERT_NO_THROW(P2 + P1);
}

TEST(Polynom, can_subtract)
{
	TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
	TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
	TPolynomial P1, P2;
	P1 += a;
	P2 += b;

	ASSERT_NO_THROW(P2 - P1);
}

TEST(Polynom, can_load_to_file)
{
	TMonom a(new double[1]{ 3 }, 1, 1);
	TMonom b(new double[1]{ 1 }, 1, 1);
	TPolynomial P1;
	P1 += a;
	P1 += b;
	ASSERT_NO_THROW(P1.LoadToFile());
}