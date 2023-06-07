<?php

	namespace Proj\Site\Units\HTML;

	require DIR_UNITS . 'statistics/site/statistics.actions.inc';
	require DIR_UNITS . 'statistics/site/statistics.model.inc';

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Closure;

	class Statistics extends Actions\Statistics {
		use Instance;

		private Model\Statistics $model;

		private function __construct() {
			parent::__construct();

			$this->model = Model\Statistics::instance();

			self::$void->Push(self::$collect, Closure::fromCallable([$this, 'Collect']));
		}

		private function Collect(): void {
			if (self::$area == 'statistics') return;

			$this->model->Collect();
		}

	}

	Statistics::init();