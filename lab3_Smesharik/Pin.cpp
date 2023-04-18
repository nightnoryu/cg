#include "Pin.h"
#include "ShapeDrawer.h"

void Pin::Draw() const
{
	DrawBody();
	DrawEyes();
	DrawBeak();
	DrawLegs();
	DrawArms();
	DrawHat();
}

void Pin::DrawBody() const
{
	ShapeDrawer::DrawFilledCircle(0, 0, 5, { 0, 0, 0 });
	ShapeDrawer::DrawFilledCircle(0, -6.5, 5, { 1, 1, 1 });
	ShapeDrawer::DrawHollowCircle(0, 0, 5, { 0, 0, 0 });
}

void Pin::DrawEyes() const
{
	ShapeDrawer::DrawFilledCircle(-1.2, 2.5, 1.2, { 1, 1, 1 });
	ShapeDrawer::DrawFilledCircle(1.2, 2.5, 1.2, { 1, 1, 1 });
	ShapeDrawer::DrawFilledCircle(-1, 2.5, 0.4, { 0, 0, 0 });
	ShapeDrawer::DrawFilledCircle(1, 2.5, 0.4, { 0, 0, 0 });
	ShapeDrawer::DrawFilledCircle(-0.8, 2.7, 0.1, { 1, 1, 1 });
	ShapeDrawer::DrawFilledCircle(1.2, 2.7, 0.1, { 1, 1, 1 });
}

void Pin::DrawBeak() const
{
	ShapeDrawer::DrawTriangle(
		{ -2.5, 1.3 },
		{ 2.5, 1.3 },
		{ 0, -1.1 },
		RED);
}

void Pin::DrawLegs() const
{
	ShapeDrawer::DrawRectangle(0.5, -6.5, 0.8, 2, RED);
	ShapeDrawer::DrawRectangle(-1.3, -6.5, 0.8, 2, RED);
	ShapeDrawer::DrawRectangle(0.5, -7.3, 2, 1, RED);
	ShapeDrawer::DrawRectangle(-2.5, -7.3, 2, 1, RED);
}

void Pin::DrawArms() const
{
	ShapeDrawer::DrawRectangle(4.4, -4.5, 1.2, 5, { 0, 0, 0 });
	ShapeDrawer::DrawRectangle(-5.6, -4.5, 1.2, 5, { 0, 0, 0 });
}

void Pin::DrawHat() const
{
	ShapeDrawer::DrawRectangle(-4, 3.5, 8, 2, PRIMARY_BROWN);
	ShapeDrawer::DrawRectangle(-4.4, 2.25, 0.8, 1.5, PRIMARY_BROWN);
	ShapeDrawer::DrawRectangle(3.6, 2.25, 0.8, 1.5, PRIMARY_BROWN);
	ShapeDrawer::DrawRectangle(-2.2, 3.55, 2, 1.5, SECONDARY_BROWN);
	ShapeDrawer::DrawRectangle(0.2, 3.55, 2, 1.5, SECONDARY_BROWN);
	ShapeDrawer::DrawRectangle(-1.9, 3.85, 1.4, 0.9, GREY);
	ShapeDrawer::DrawRectangle(0.5, 3.85, 1.4, 0.9, GREY);
}
