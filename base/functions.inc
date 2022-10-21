<?php

	use JetBrains\PhpStorm\NoReturn;

	/**
	 * Отправка JSON данных
	 * @param string $string - Строка JSON
	 */
	#[NoReturn] function SendJSON(string $string) {
		header("Cache-Control: no-cache, no-store, must-revalidate");
		header('Content-Type: application/json; charset=utf-8');
		die($string);
	}

	/**
	 * Кодирование и отправка данных JSON
	 * @param $data - Данные для кодирования
	 */
	#[NoReturn] function SendJSONData($data) {
		SendJSON(json_encode($data));
	}

	/**
	 * Отправка положительного ответа
	 * @param $data - Данные
	 */
	#[NoReturn] function SendJSONSuccess($data) {
		SendJSONData(['state' => 'ok', 'data' => $data]);
	}

	/**
	 * Возвращает значение параметра запроса
	 * @param string $post_name - Имя POST-параметра
	 * @param string $get_name - Имя GET-параметра
	 * @param $default - Значение по умолчанию
	 * @return mixed
	 */
	function GetParam(string $post_name, string $get_name, $default) {
		if (isset($_POST[$post_name])) return $_POST[$post_name];
		if (isset($_GET[$get_name])) return $_GET[$get_name];
		return $default;
	}

	/**
	 * Проверяет можно ли выводить отладочную информацию
	 * @return bool
	 */
	function CheckDebugger() :bool {
		return (DEBUG);
	}

	/**
	 * Вывод отладочной информации
	 * @param $var - Переменная для вывода
	 * @param string $title - Заголовок
	 */
	function Debug($var, string $title = '') :void {
		if (!CheckDebugger()) return;

		echo "<b>{$title}</b><pre>";
		var_dump($var);
		echo "</pre>";
	}