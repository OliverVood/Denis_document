<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'general/admin/general.actions.inc';
	require DIR_UNITS . 'general/admin/general.model.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Response;

	class General extends Actions\General {
		use Instance;

		private function __construct() {
			parent::__construct();

			self::$view->Push(self::$home, [$this, 'Home']);
			self::$view->Push(self::$db_structure, [$this, 'Structure']);
			self::$view->Push(self::$db_check, [$this, 'Check']);
			self::$view->Push(self::$db_make, [$this, 'Make']);
		}

		#[NoReturn] public function Home() {
			Response::PushHistory(self::$home);
			Response::PushSection('main', Model\General::instance()->Home());
			Response::SendJSON();
		}

		#[NoReturn] public function Structure() {
			Response::PushHistory(self::$db_structure);
			Response::PushSection('main', Model\General::instance()->Structure());
			Response::SendJSON();
		}

		#[NoReturn] public function Check() {
			Response::PushHistory(self::$db_check, [], 'Admin.General.Render.CheckDB');
			Response::PushData(Model\General::instance()->DBCheck());
			Response::SendJSON();
		}

		#[NoReturn] public function Make() {
			Response::PushData(Model\General::instance()->DBMake());
			Response::SendJSON();
		}

	}

	General::init();