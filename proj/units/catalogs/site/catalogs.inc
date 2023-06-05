<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'catalogs/consts.inc';
	require DIR_UNITS . 'catalogs/site/views/buttons.tpl';
	require DIR_UNITS . 'catalogs/site/views/estimate.tpl';
	require DIR_UNITS . 'catalogs/site/views/certificate.tpl';
	require DIR_UNITS . 'catalogs/site/views/priceList.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\Site\Params;
	use Proj\Site\Templates\Template;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General\Buttons;
	use Proj\Site\Templates\Catalogs\Estimate;
	use Proj\Site\Templates\Catalogs\Certificate;
	use Proj\Site\Templates\Catalogs\PriceList;

	class Catalogs extends Units implements Consts\Catalogs {
		use Instance;

		public Action $out_buttons;
		public Action $action_estimate;
		public Action $action_certificate;
		public Action $action_price_list;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->out_buttons = new Action('null', 'null');
			$this->action_estimate = new Action('estimate', 'null', '/estimate');
			$this->action_certificate = new Action('certificate', 'null', '/certificate');
			$this->action_price_list = new Action('price_list', 'null', '/price_list');

			self::$view->Push($this->out_buttons, [$this, 'OutButtons']);
			self::$view->Push($this->action_estimate, [$this, 'OutEstimate']);
			self::$view->Push($this->action_certificate, [$this, 'OutCertificate']);
			self::$view->Push($this->action_price_list, [$this, 'OutPriceList']);
		}

		public function OutButtons() {
			Layout::instance()->main->Push(Buttons::ToVar());
		}

		public function OutEstimate() {
			Template::instance()->SetTitle(Params::$site_name . ' | Сметы');
			Template::instance()->SetDescription('Составление сметы на оказание услуг и продажу товаров');
			Template::instance()->SetKeywords('смета онлайн бесплатно, документы для самозанятых');
			Layout::instance()->main->Push(Estimate::ToVar());
		}

		public function OutCertificate() {
			Template::instance()->SetTitle(Params::$site_name . ' | Акты выполненных работ');
			Template::instance()->SetDescription('акт выполненных работ, для ИП, отчёты');
			Template::instance()->SetKeywords('');
			Layout::instance()->main->Push(Certificate::ToVar());
		}

		public function OutPriceList() {
			Template::instance()->SetTitle(Params::$site_name . ' | Прайс-листы');
			Template::instance()->SetDescription('Составление прайс-листа на оказание услуг, проведение работ и продажу товаров');
			Template::instance()->SetKeywords('прайс-лист онлайн, отчет оказание услуг, перечень цен на товары');
			Layout::instance()->main->Push(PriceList::ToVar());
		}

	}

	Catalogs::init();