<?php

	namespace Proj\Admin\Units\HTML;

	require DIR_UNITS . 'general/admin/general.actions.inc';
	require DIR_UNITS . 'general/admin/general.model.inc';
	require DIR_UNITS . 'general/admin/views/group.tpl';

	use Base\Instance;
	use Proj\Params;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Item;
	use Proj\Admin\Templates\General\Group;

	class General extends Actions\General {
		use Instance;

		private Model\General $model;

		private function __construct() {
			parent::__construct();

			$this->model = Model\General::instance();

			self::$view->Push(self::$out_head, [$this, 'OutHead']);
			self::$view->Push(self::$out_menu, [$this, 'OutMenu']);
			self::$view->Push(self::$out_footer, [$this, 'OutFooter']);
			self::$view->Push(self::$home, [$this, 'Home']);
			self::$view->Push(self::$db_structure, [$this, 'Structure']);
			self::$view->Push(self::$db_check, [$this, 'Check']);
		}

		public function OutHead(): void {
			Layout::instance()->header->Push("<div>Привет, " . USER_LOGIN . "</div>");
			Layout::instance()->header->Push(Actions\Users::$exit->GetLinkHref('', [], ['class' => 'logout']));
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(Item::ToVar('<a href = "' . self::$site->GetAddress() . '" target = "_blank">Открыть сайт</a>'));
			Layout::instance()->menu->Push(Item::ToVar(self::$home->GetLinkHref('Главная')));
			Layout::instance()->menu->Push(
				Group::ToVar('База данных', [
					self::$db_structure->GetLinkHref('Структура'),
					self::$db_check->GetLinkHref('Проверить')
				])
			);
		}

		public function OutFooter() {
			Layout::instance()->footer->Push('© ' . Params::$site_name);
		}

		public function Structure() {
			Layout::instance()->main->Push($this->model->Structure());
		}

		public function Home() {
			Layout::instance()->main->Push($this->model->Home());
		}

		public function Check() {
			$result = json_encode($this->model->DBCheck());
			Layout::instance()->js_loaded->Push(/** @lang JavaScript */ "Admin.General.Render.CheckDB({$result});");
		}

	}

	General::init();