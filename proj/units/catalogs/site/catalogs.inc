<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'catalogs/consts.inc';
	require 'views/work.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Catalogs\Work;

	class Catalogs extends Units implements Consts\Catalogs {
		use Instance;

		private Action $act_catalogs;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->act_catalogs = new Action('null', 'null');

			Controller::instance()->view->Push($this->act_catalogs, [$this, 'OutCatalog']);
		}

		public function OutCatalog() {
			Layout::instance()->main->Push(Work::object()->ToVar());
		}

	}

	Catalogs::init();