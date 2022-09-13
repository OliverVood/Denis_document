<?php

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
	function Debug($var, $title = '') :void {
		if (!CheckDebugger()) return;

		echo "<b>{$title}</b><pre>";
		var_dump($var);
		echo "</pre>";
	}