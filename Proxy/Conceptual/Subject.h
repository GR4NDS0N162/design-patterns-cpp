#pragma once

/// <summary>
/// <para>
/// �������:
/// </para>
/// <para>
/// - ���������� ����� ��� RealSubject � Proxy ���������.
/// </para>
/// <para>
/// - ������ ����������� �����  ������������ ���, ��� 
/// ��������� ������ �������.
/// </para>
/// </summary>
class Subject {
public:
	virtual void Request() const = 0;
};

