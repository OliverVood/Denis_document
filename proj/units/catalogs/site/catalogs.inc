<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'catalogs/consts.inc';
	require 'views/estimate.tpl';
	require 'views/certificate.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Catalogs\Estimate;
	use Proj\Site\Templates\Catalogs\Certificate;

	class Catalogs extends Units implements Consts\Catalogs {
		use Instance;

		private Action $act_estimate;
		private Action $act_certificate;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->act_estimate = new Action('estimate', 'null');
			$this->act_certificate = new Action('certificate', 'null');

			Controller::instance()->view->Push($this->act_estimate, [$this, 'OutEstimate']);
			Controller::instance()->view->Push($this->act_certificate, [$this, 'OutCertificate']);
		}

		public function OutEstimate() {
			Layout::instance()->main->Push(Estimate::object()->ToVar());
		}

		public function OutCertificate() {
			Layout::instance()->main->Push(Certificate::object()->ToVar());
		}

	}

	Catalogs::init();