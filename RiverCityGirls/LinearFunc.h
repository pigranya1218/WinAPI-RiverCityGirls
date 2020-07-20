#pragma once

enum class LINEAR_VALUE_TYPE
{
	UP, // ������ ���� ����
	ON, // ���� ���� ��������
	DOWN // ������ �Ʒ��� ����
};

// 1�� �Լ�, ������ �������� ���Ʒ� ��� ��ġ�ϴ��� �Ǵ��ϴ� �޼��� ����
class LinearFunc
{
public:
	SynthesizePublic(float, a, A); // x ����
	SynthesizePublic(float, b, B); // y ����

private:
	LinearFunc() {}

public:
	LinearFunc(float a, float b) :a(a), b(b) {}
	LinearFunc(Vector2 start, Vector2 end);

	LINEAR_VALUE_TYPE getValueType(float x, float y);
	
	float getX(float y) { return (y - b) / a; }
	float getY(float x) { return a * x + b; }

public:
	static LinearFunc getLinearFuncFromPoints(Vector2 start, Vector2 end);


};

