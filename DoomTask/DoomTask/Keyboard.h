#pragma once

#include <queue>
#include <bitset>
#include <optional>

/// <summary>
/// Class for handling the keyboard input
/// </summary>
class Keyboard
{
	friend class DTWindow;
public: 
#pragma region nested class

	/// <summary>
	/// Events of the keyboard keys
	/// </summary>
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};

		Event() noexcept;
		Event(Type type, unsigned char code) noexcept;
		bool IsPress() const noexcept;
		bool IsRelease() const noexcept;
		unsigned char GetCode() const noexcept;

	private:
		Type type;
		unsigned char code;
	};

	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	
	bool KeyIsPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void ClearKey() noexcept;
	
	char ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void ClearChar() noexcept;
	void Clear() noexcept;
	
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnabled() const noexcept;
#pragma endregion

private: 
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;

	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;
};

