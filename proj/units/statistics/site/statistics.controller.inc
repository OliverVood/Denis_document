<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'statistics/site/statistics.actions.inc';
	require DIR_UNITS . 'statistics/site/statistics.model.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Helper\Response;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Closure;

	class Statistics extends Actions\Statistics {
		use Instance;

		private Model\Statistics $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Statistics::instance();

			self::$void->Push([self::ENTRY_HTML, self::ENTRY_XHR], self::$collect, Closure::fromCallable([$this, 'Collect']));
			self::$view->Push([self::ENTRY_XHR], self::$act, Closure::fromCallable([$this, 'DoAct']));
		}

		#region HTML XHR

		private function Collect(): void {
			$this->model->Collect();
		}

		#endregion HTML XHR

		#region XHR

		#[NoReturn] private function DoAct(): void {
			$cid = Model\Users::GetCID();
			$object = GetParam('object', '');
			$action = GetParam('action', '');
			$params = GetParam('params', '');

			$this->model->InsertAct($cid, $object, $action, $params);

			Response::SendJSON();
		}

		#endregion XHR

	}

	Statistics::init();