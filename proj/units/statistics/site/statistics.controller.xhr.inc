<?php

	namespace Proj\Site\Units\XHR;

	require DIR_UNITS . 'statistics/site/statistics.actions.inc';
	require DIR_UNITS . 'statistics/site/statistics.model.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Response;

	class Statistics extends Actions\Statistics {
		use Instance;

		private Model\Statistics $model;

		private function __construct() {
			parent::__construct();
			$this->model = Model\Statistics::instance();

			self::$void->Push(self::$collect, [$this, 'Collect']);
			self::$view->Push(self::$act, [$this, 'DoAct']);
		}

		public function Collect(): void {
			if (self::$area == 'statistics') return;

			$this->model->Collect();
		}

		#[NoReturn] public function DoAct(): void {
			$uid = Model\Users::GetUID();
			$object = GetParam('object', '');
			$action = GetParam('action', '');
			$params = GetParam('params', '');

			$this->model->InsertAct($uid, $object, $action, $params);

			Response::SendJSON();
		}

	}

	Statistics::init();