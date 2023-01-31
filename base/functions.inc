<?php

	use JetBrains\PhpStorm\NoReturn;

	/**
	 * Отправка JSON данных
	 * @param string $string - Строка JSON
	 * @return void
	 */
	#[NoReturn] function SendJSON(string $string): void {
		header("Cache-Control: no-cache, no-store, must-revalidate");
		header('Content-Type: application/json; charset=utf-8');
		die($string);
	}

	/**
	 * Кодирование и отправка данных JSON
	 * @param array $data - Данные для кодирования
	 * @return void
	 */
	#[NoReturn] function SendJSONData(array $data): void {
		SendJSON(json_encode($data));
	}

	/**
	 * Отправка положительного ответа
	 * @param mixed $data - Данные
	 * @return void
	 */
	#[NoReturn] function SendJSONSuccess(mixed $data): void {
		SendJSONData(['state' => 'ok', 'data' => $data]);
	}

	/**
	 * Возвращает значение параметра запроса
	 * @param string $key - Ключ POST/GET параметра
	 * @param mixed $default - Значение по умолчанию
	 * @return mixed
	 */
	function GetParam(string $key, mixed $default = null): mixed {
		return $_POST[$key] ?? $_GET[$key] ?? $default;
	}

	/**
	 * Возвращает значение параметра запроса
	 * @param string $key - Ключ POST/GET параметра
	 * @param int $default - Значение по умолчанию
	 * @return int
	 */
	function GetInt(string $key, int $default = 0): int {
		return (int)GetParam($key, $default);
	}

	/**
	 * Проверяет можно ли выводить отладочную информацию
	 * @return bool
	 */
	function CheckDebugger(): bool {
		return DEBUG;
	}

	/**
	 * Вывод отладочной информации
	 * @param mixed $var - Переменная для вывода
	 * @param string $title - Заголовок
	 * @return void
	 */
	function Debug(mixed $var, string $title = ''): void {
		if (!CheckDebugger()) return;

		echo "<b>{$title}</b><pre>";
		var_dump($var);
		echo "</pre>";
	}

	/**
	 * Получить IP пользователя
	 * @return string
	 */
	function GetUserIP(): string {
		$client = @$_SERVER['HTTP_CLIENT_IP'];
		$forward = @$_SERVER['HTTP_X_FORWARDED_FOR'];
		$remote = @$_SERVER['REMOTE_ADDR'];

		if (filter_var($client, FILTER_VALIDATE_IP)) return $client;
		elseif (filter_var($forward, FILTER_VALIDATE_IP)) return $forward;
		else return $remote;
	}