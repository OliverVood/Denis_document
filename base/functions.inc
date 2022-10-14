<?php

	use JetBrains\PhpStorm\NoReturn;

	/**
	 * Отправка JSON данных
	 * @param string $string - строка JSON
	 */
	#[NoReturn] function SendJSON(string $string) {
		header("Cache-Control: no-cache, no-store, must-revalidate");
		header('Content-Type: application/json; charset=utf-8');
		die($string);
	}

	/**
	 * Кодирование и отправка данных JSON
	 * @param $data - данные для кодирования
	 */
	#[NoReturn] function SendJSONData($data) {
		SendJSON(json_encode($data));
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