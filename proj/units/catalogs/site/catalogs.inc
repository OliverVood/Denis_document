<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'catalogs/consts.inc';
	require 'views/estimate.tpl';
	require 'views/certificate.tpl';
	require 'views/price_list.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Catalogs\Estimate;
	use Proj\Site\Templates\Catalogs\Certificate;
	use Proj\Site\Templates\Catalogs\PriceList;

	class Catalogs extends Units implements Consts\Catalogs {
		use Instance;

		public Action $action_estimate;
		public Action $action_certificate;
		public Action $action_price_list;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->action_estimate = new Action('estimate', 'null', '/estimate');
			$this->action_certificate = new Action('certificate', 'null', '/certificate');
			$this->action_price_list = new Action('price_list', 'null', '/price_list');

			Controller::instance()->view->Push($this->action_estimate, [$this, 'OutEstimate']);
			Controller::instance()->view->Push($this->action_certificate, [$this, 'OutCertificate']);
			Controller::instance()->view->Push($this->action_price_list, [$this, 'OutPriceList']);
		}

		public function OutEstimate() {
			Layout::instance()->main->Push(Estimate::object()->ToVar());
		}

		public function OutCertificate() {
			Layout::instance()->main->Push(Certificate::object()->ToVar());
		}

		public function OutPriceList() {
			Layout::instance()->main->Push(PriceList::object()->ToVar());
		}

	}

	Catalogs::init();