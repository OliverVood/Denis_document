<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'general/admin/general.actions.inc';
	require DIR_UNITS . 'general/admin/general.model.inc';
	require DIR_UNITS . 'general/admin/views/structure.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Proj\Admin\Templates\General AS TPL;
	use Response;
	use Closure;

	class General extends Actions\General {
		use Instance;

		private Model\General $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\General::instance();

			self::$view->Push(self::$home, Closure::fromCallable([$this, 'Home']));
			self::$view->Push(self::$db_structure, Closure::fromCallable([$this, 'Structure']));
			self::$view->Push(self::$db_check, Closure::fromCallable([$this, 'Check']));
			self::$view->Push(self::$db_make, Closure::fromCallable([$this, 'Make']));
		}

		#[NoReturn] private function Home() {
			Response::PushHistory(self::$home);
			Response::PushSection('main', $this->model->Home());
			Response::SendJSON();
		}

		#[NoReturn] private function Structure() {
			Response::PushHistory(self::$db_structure);
			Response::PushSection('main', TPL\Structure::ToVar($this->model->Structure()));
			Response::SendJSON();
		}

		#[NoReturn] private function Check() {
			Response::PushHistory(self::$db_check, [], 'Admin.General.Render.CheckDB');
			Response::PushData($this->model->DBCheck());
			Response::SendJSON();
		}

		#[NoReturn] private function Make() {
			Response::PushData($this->model->DBMake());
			Response::SendJSON();
		}

	}

	General::init();