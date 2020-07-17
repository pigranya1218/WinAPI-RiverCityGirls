#pragma once

class FloatRect final
{
public:
	float left;
	float top;
	float right;
	float bottom;
public:
	FloatRect();
	explicit FloatRect(const float& left, const float& top, const float& right, const float& bottom);
	explicit FloatRect(const int& left, const int& top, const int& right, const int& bottom);
	explicit FloatRect(const Vector2& pos, const Vector2& size, const Pivot& pivot);
	explicit FloatRect(const RECT& rc);

	const RECT GetRect();
	float GetWidth();
	float GetHeight();
	Vector2 GetCenter();
	Vector2 GetBottom();
	Vector2 GetSize();
	void Update(const Vector2& pos, const Vector2& size, const Pivot& pivot);
	void Move(const Vector2& moveValue);

	const FloatRect& operator=(const RECT& rc);
};

inline FloatRect RectMakePivot(const Vector2& pos, const Vector2& size, const Pivot& pivot)
{
	FloatRect result;
	switch (pivot)
	{
	case Pivot::LeftTop:
		result.left = pos.x;
		result.top = pos.y;
		result.right = pos.x + size.x;
		result.bottom = pos.y + size.y;
		return result;
	case Pivot::Center:
		result.left = pos.x - size.x / 2.f;
		result.top = pos.y - size.y / 2.f;
		result.right = pos.x + size.x / 2.f;
		result.bottom = pos.y + size.y / 2.f;
		return result;
	case Pivot::Bottom:
		result.left = pos.x - size.x / 2.f;
		result.top = pos.y - size.y;
		result.right = pos.x + size.x / 2.f;
		result.bottom = pos.y;
		return result;
	}
	return result;
}