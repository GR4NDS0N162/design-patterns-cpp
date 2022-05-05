#pragma once

/// <summary>
/// <para>
/// Субъект:
/// </para>
/// <para>
/// - определяет общий для RealSubject и Proxy интерфейс.
/// </para>
/// <para>
/// - объект заместителя можно  использовать там, где 
/// ожидается объект сервиса.
/// </para>
/// </summary>
class Subject {
public:
	virtual void Request() const = 0;
};

