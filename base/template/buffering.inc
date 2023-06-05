<?php

	namespace Base\Templates;

	abstract class Buffering {

		public static function Start(): void {
			ob_start();
		}

		public static function Read(): string {
			$val = ob_get_contents();
			ob_end_clean();

			return $val !== false ? $val : '';
		}

	}