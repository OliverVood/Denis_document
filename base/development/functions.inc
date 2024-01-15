<?php

	use JetBrains\PhpStorm\NoReturn;

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