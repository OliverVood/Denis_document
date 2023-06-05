<?php

	use JetBrains\PhpStorm\NoReturn;

	use Base\Action;

	class Response {
		public static array $stack = [];

		public static function PushSection(string $section, string $html, bool $empty = true): void {
			self::Push('section', ['section' => $section, 'html' => $html, 'empty' => $empty]);
		}

		public static function PushHistory(Action $action, array $data = [], string $handler = null): void {
			if (GetInt('no_history')) return;
			self::Push('history', ['address' => $action->GetAddress($data), 'xhr' => $action->GetXHR($data), 'handler' => $handler]);
		}

		public static function PushNoticeOk(string $notice): void {
			self::PushNotice('ok', $notice);
		}

		public static function PushNoticeInfo(string $notice): void {
			self::PushNotice('info', $notice);
		}

		public static function PushNoticeError(string $notice): void {
			self::PushNotice('error', $notice);
		}

		private static function PushNotice(string $type, string $notice): void {
			self::Push('notice', ['type' => $type, 'notice' => $notice]);
		}

		public static function PushData($data): void {
			self::Push('data', $data);
		}

		private static function Push(string $type = '', array $data = []): void {
			self::$stack[] = ['type' => $type, 'data' => $data];
		}

		#[NoReturn] public static function SendJSON(): void {
			SendJSONData(self::$stack);
		}

	}