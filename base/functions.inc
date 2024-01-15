<?php

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