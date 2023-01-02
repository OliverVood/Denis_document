<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'general/consts.inc';
	require 'views/menu.tpl';
	require 'views/main.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General\Menu;
	use Proj\Site\Templates\General\Main;

	class General extends Units implements Consts\General {
		use Instance;

		private Action $out_menu;
		private Action $out_main;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->out_menu		= new Action('always', 'always');
			$this->out_main		= new Action('null', 'null');

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
			Controller::instance()->view->Push($this->out_main, [$this, 'OutMain']);
		}

		public function OutMenu() {
			Layout::instance()->header->Push(Menu::object()->ToVar());
		}

		public function OutMain() {
			Layout::instance()->main->Push(Main::object()->ToVar());
		}

	}

	General::init();