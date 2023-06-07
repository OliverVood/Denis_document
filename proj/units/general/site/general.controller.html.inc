<?php

	namespace Proj\Site\Units\HTML;

	require DIR_UNITS . 'general/site/general.actions.inc';
	require DIR_UNITS . 'general/site/views/About.tpl';
	require DIR_UNITS . 'general/site/views/Contacts.tpl';
	require DIR_UNITS . 'general/site/views/PrivacyPolicy.tpl';
	require DIR_UNITS . 'general/site/views/TermsUse.tpl';
	require DIR_UNITS . 'general/site/views/Header.tpl';
	require DIR_UNITS . 'general/site/views/Footer.tpl';

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Params;
	use Proj\Site\Templates\Template;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General as TPL;

	class General extends Actions\General {
		use Instance;

		private function __construct() {
			parent::__construct();

			self::$view->Push(self::$set_data_page, [$this, 'SetDataPage']);

			self::$view->Push(self::$home, [$this, 'Home']);
			self::$view->Push(self::$about, [$this, 'About']);
			self::$view->Push(self::$contacts, [$this, 'Contacts']);
			self::$view->Push(self::$privacy_policy, [$this, 'OutPrivacyPolicy']);
			self::$view->Push(self::$terms_use, [$this, 'OutTermsUse']);
			self::$view->Push(self::$error404, [$this, 'Error404']);

			self::$view->Push(self::$header, [$this, 'OutHeader']);
			self::$view->Push(self::$header, [$this, 'OutFooter']);
		}

		public function SetDataPage() {
			$path = [];
			if (self::$area != 'null') $path[] = self::$area;
			if (self::$part != 'null') $path[] = self::$part;
			$value = $path ? implode('_', $path) : 'main';
			Template::instance()->SetDataPage($value);
		}

		public function Home() {
			Template::instance()->SetTitle(Params::$site_name . ' | Главная');
			Template::instance()->SetDescription(Params::$site_name . ' - ресурс в помощь ИП, самозанятым с документами и отчётами');
			Template::instance()->SetKeywords('прайс-лист онлайн, составить акт выполненных работ, смета бесплатно, документы для ИП, отчёты самозанятые');
		}

		public function About() {
			Template::instance()->SetTitle(Params::$site_name . ' | О проекте');
			Template::instance()->SetDescription('О проекте ' . Params::$site_name);
			Template::instance()->SetKeywords('проект ' . Params::$site_name);
			Layout::instance()->main->Push(TPL\About::ToVar());
		}

		public function Contacts() {
			Template::instance()->SetTitle(Params::$site_name . ' | Контакты');
			Template::instance()->SetDescription('Контакты');
			Template::instance()->SetKeywords('контакты');
			Layout::instance()->main->Push(TPL\Contacts::ToVar());
		}

		public function OutPrivacyPolicy() {
			Template::instance()->SetTitle(Params::$site_name . ' | Политика конфиденциальности');
			Template::instance()->SetDescription('Политика конфиденциальности ' . Params::$site_name);
			Template::instance()->SetKeywords('политика конфиденциальности');
			Layout::instance()->main->Push(TPL\PrivacyPolicy::ToVar());
		}

		public function OutTermsUse() {
			Template::instance()->SetTitle(Params::$site_name . ' | Пользовательское соглашение');
			Template::instance()->SetDescription('Пользовательское соглашение ' . Params::$site_name);
			Template::instance()->SetKeywords('пользовательское соглашение');
			Layout::instance()->main->Push(TPL\TermsUse::ToVar());
		}

		public function OutHeader() {
			Layout::instance()->header->Push(TPL\Header::ToVar());
		}

		public function OutFooter() {
			Layout::instance()->footer->Push(TPL\Footer::ToVar());
		}

		public function Error404() {
			Layout::instance()->main->Push('<h1>Страница не найдена!<h1>');
		}

	}

	General::init();