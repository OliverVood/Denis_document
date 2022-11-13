<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'general/consts.inc';
	require 'views/menu.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General\Menu;

	class General extends Units implements Consts\General {
		use Instance;

		private Action $out_menu;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->out_menu		= new Action('always', 'always');

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->header->Push(Menu::object()->ToVar());
		}

	}

	General::init();