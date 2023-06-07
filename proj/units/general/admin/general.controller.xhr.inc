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

		private Model\General $model;

		private function __construct() {
			parent::__construct();

			$this->model = Model\General::instance();

			self::$view->Push(self::$home, [$this, 'Home']);
			self::$view->Push(self::$db_structure, [$this, 'Structure']);
			self::$view->Push(self::$db_check, [$this, 'Check']);
			self::$view->Push(self::$db_make, [$this, 'Make']);
		}

		#[NoReturn] public function Home() {
			Response::PushHistory(self::$home);
			Response::PushSection('main', $this->model->Home());
			Response::SendJSON();
		}

		#[NoReturn] public function Structure() {
			Response::PushHistory(self::$db_structure);
			Response::PushSection('main', $this->model->Structure());
			Response::SendJSON();
		}

		#[NoReturn] public function Check() {
			Response::PushHistory(self::$db_check, [], 'Admin.General.Render.CheckDB');
			Response::PushData($this->model->DBCheck());
			Response::SendJSON();
		}

		#[NoReturn] public function Make() {
			Response::PushData($this->model->DBMake());
			Response::SendJSON();
		}

	}

	General::init();