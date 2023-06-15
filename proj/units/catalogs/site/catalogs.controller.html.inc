<?php

	namespace Proj\Site\Units\HTML;

	require DIR_UNITS . 'catalogs/site/catalogs.actions.inc';
	require DIR_UNITS . 'catalogs/site/views/buttons.tpl';
	require DIR_UNITS . 'catalogs/site/views/estimate.tpl';
	require DIR_UNITS . 'catalogs/site/views/certificate.tpl';
	require DIR_UNITS . 'catalogs/site/views/priceList.tpl';

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Templates\Template;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Catalogs as TPL;
	use Proj\Params;
	use Closure;

	class Catalogs extends Actions\Catalogs {
		use Instance;

		private function __construct() {
			parent::__construct();

			self::$view->Push(self::$out_buttons, Closure::fromCallable([$this, 'OutButtons']));
			self::$view->Push(self::$action_estimate, Closure::fromCallable([$this, 'OutEstimate']));
			self::$view->Push(self::$action_certificate, Closure::fromCallable([$this, 'OutCertificate']));
			self::$view->Push(self::$action_price_list, Closure::fromCallable([$this, 'OutPriceList']));
		}

		private function OutButtons(): void {
			Layout::instance()->main->Push(TPL\Buttons::ToVar());
		}

		private function OutEstimate(): void {
			Template::instance()->SetTitle(Params::$site_name . ' | Сметы');
			Template::instance()->SetDescription('Составление сметы на оказание услуг и продажу товаров');
			Template::instance()->SetKeywords('смета онлайн бесплатно, документы для самозанятых');
			Layout::instance()->main->Push(TPL\Estimate::ToVar());
		}

		private function OutCertificate(): void {
			Template::instance()->SetTitle(Params::$site_name . ' | Акты выполненных работ');
			Template::instance()->SetDescription('акт выполненных работ, для ИП, отчёты');
			Template::instance()->SetKeywords('');
			Layout::instance()->main->Push(TPL\Certificate::ToVar());
		}

		private function OutPriceList(): void {
			Template::instance()->SetTitle(Params::$site_name . ' | Прайс-листы');
			Template::instance()->SetDescription('Составление прайс-листа на оказание услуг, проведение работ и продажу товаров');
			Template::instance()->SetKeywords('прайс-лист онлайн, отчет оказание услуг, перечень цен на товары');
			Layout::instance()->main->Push(TPL\PriceList::ToVar());
		}

	}

	Catalogs::init();