<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'general/consts.inc';
	require DIR_UNITS . 'general/site/views/Header.tpl';
	require DIR_UNITS . 'general/site/views/Footer.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General\Header;
	use Proj\Site\Templates\General\Footer;

	class General extends Units implements Consts\General {
		use Instance;

		private Action $out_header;
		private Action $out_footer;
		private Action $set_data_page;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->set_data_page	= new Action('always', 'always');

			$this->out_header		= new Action('always', 'always');
			$this->out_footer		= new Action('always', 'always');

			Controller::instance()->view->Push($this->set_data_page, [$this, 'SetDataPage']);

			Controller::instance()->view->Push($this->out_header, [$this, 'OutHeader']);
			Controller::instance()->view->Push($this->out_header, [$this, 'OutFooter']);
		}

		public function OutHeader() {
			Layout::instance()->header->Push(Header::object()->ToVar());
		}

		public function OutFooter() {
			Layout::instance()->footer->Push(Footer::object()->ToVar());
		}

		public function SetDataPage() {
			$path = [];
			if (Controller::$area != 'null') $path[] = Controller::$area;
			if (Controller::$part != 'null') $path[] = Controller::$part;
			$value = $path ? implode('_', $path) : 'main';
			Layout::SetDataPage($value);
		}

	}

	General::init();