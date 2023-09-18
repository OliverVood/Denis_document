<?php

	use JetBrains\PhpStorm\NoReturn;

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
	 * Вывод отладочной информации с остановкой скрипта
	 * @param mixed $var - Переменная для вывода
	 * @param string $title - Заголовок
	 * @return void
	 */
	#[NoReturn] function dd(mixed $var, string $title = ''): void {
		Debug($var, $title);
		die;
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