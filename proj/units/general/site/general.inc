<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'general/consts.inc';
	require DIR_UNITS . 'general/site/views/About.tpl';
	require DIR_UNITS . 'general/site/views/Contacts.tpl';
	require DIR_UNITS . 'general/site/views/PrivacyPolicy.tpl';
	require DIR_UNITS . 'general/site/views/TermsUse.tpl';
	require DIR_UNITS . 'general/site/views/Header.tpl';
	require DIR_UNITS . 'general/site/views/Footer.tpl';
	require DIR_UNITS . 'general/site/views/Donations.tpl';

	use Base\Units;
	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use JetBrains\PhpStorm\NoReturn;
	use Proj\Units\Consts;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\General\About;
	use Proj\Site\Templates\General\Contacts;
	use Proj\Site\Templates\General\PrivacyPolicy;
	use Proj\Site\Templates\General\TermsUse;
	use Proj\Site\Templates\General\Header;
	use Proj\Site\Templates\General\Footer;
	use Proj\Site\Templates\General\Donations;

	class General extends Units implements Consts\General {
		use Instance;

		public Action $set_data_page;

		public Action $home;
		public Action $about;
		public Action $contacts;
		public Action $privacy_policy;
		public Action $terms_use;

		public Action $header;
		public Action $footer;

		public Action $donations;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);

			$this->set_data_page			= new Action('always', 'always');

			$this->home						= new Action('null', 'null', 'default');
			$this->about					= new Action('about', 'null', 'default');
			$this->contacts					= new Action('contacts', 'null', 'default');
			$this->privacy_policy			= new Action('documents', 'privacy_policy', 'default');
			$this->terms_use				= new Action('documents', 'terms_use', 'default');

			$this->header					= new Action('always', 'always');
			$this->footer					= new Action('always', 'always');

			$this->donations				= new Action('donations', 'null', 'default', /* @lang JavaScript */ "Site.General.On(); return false;");

			Controller::instance()->view->Push($this->set_data_page, [$this, 'SetDataPage']);

			Controller::instance()->view->Push($this->about, [$this, 'About']);
			Controller::instance()->view->Push($this->contacts, [$this, 'Contacts']);
			Controller::instance()->view->Push($this->privacy_policy, [$this, 'OutPrivacyPolicy']);
			Controller::instance()->view->Push($this->terms_use, [$this, 'OutTermsUse']);

			Controller::instance()->view->Push($this->header, [$this, 'OutHeader']);
			Controller::instance()->view->Push($this->header, [$this, 'OutFooter']);

			Controller::instance()->view->Push($this->donations, [$this, 'OnDonations']);
		}

		public function SetDataPage() {
			$path = [];
			if (Controller::$area != 'null') $path[] = Controller::$area;
			if (Controller::$part != 'null') $path[] = Controller::$part;
			$value = $path ? implode('_', $path) : 'main';
			Layout::SetDataPage($value);
		}

		public function About() {
			Layout::instance()->main->Push(About::object()->ToVar());
		}

		public function Contacts() {
			Layout::instance()->main->Push(Contacts::object()->ToVar());
		}

		public function OutPrivacyPolicy() {
			Layout::instance()->main->Push(PrivacyPolicy::object()->ToVar());
		}

		public function OutTermsUse() {
			Layout::instance()->main->Push(TermsUse::object()->ToVar());
		}

		public function OutHeader() {
			Layout::instance()->header->Push(Header::object()->ToVar());
		}

		public function OutFooter() {
			Layout::instance()->footer->Push(Footer::object()->ToVar());
		}

		#[NoReturn] public function OnDonations() {
			SendJSONSuccess(['html' => Donations::object()->ToVar()]);
		}

	}

	General::init();