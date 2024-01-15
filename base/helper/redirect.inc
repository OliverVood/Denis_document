<?php

	use JetBrains\PhpStorm\NoReturn;

	abstract class Redirect {

		#[NoReturn] public static function Page404(): void {
			header("Location: /404"); die;
		}

	}