<?php

	namespace Proj\Site\Units\XHR;

	require DIR_UNITS . 'general/site/general.actions.inc';
	require DIR_UNITS . 'general/site/views/Donations.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Templates\General as TPL;
	use Response;
	use Closure;

	class General extends Actions\General {
		use Instance;

		private function __construct() {
			parent::__construct();

			self::$view->Push(self::$donations, Closure::fromCallable([$this, 'OnDonations']));
		}

		#[NoReturn] private function OnDonations() {
			Response::PushData(['html' => TPL\Donations::ToVar()]);
			Response::SendJSON();
		}

	}

	General::init();