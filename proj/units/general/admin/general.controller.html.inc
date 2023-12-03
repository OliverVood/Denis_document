<?php

	namespace Proj\Admin\Units\HTML;

	require DIR_UNITS . 'general/admin/general.actions.inc';
	require DIR_UNITS . 'general/admin/general.model.inc';
	require DIR_UNITS . 'general/admin/views/group.tpl';
	require DIR_UNITS . 'general/admin/views/structure.tpl';

	use Base\Instance;
	use Proj\Params;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General AS TPL;
	use Closure;

	class General extends Actions\General {
		use Instance;

		private Model\General $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\General::instance();

			self::$view->Push(self::$out_head, Closure::fromCallable([$this, 'OutHead']));
			self::$view->Push(self::$out_menu, Closure::fromCallable([$this, 'OutMenu']));
			self::$view->Push(self::$out_footer, Closure::fromCallable([$this, 'OutFooter']));
			self::$view->Push(self::$home, Closure::fromCallable([$this, 'Home']));
			self::$view->Push(self::$db_structure, Closure::fromCallable([$this, 'Structure']));
			self::$view->Push(self::$db_check, Closure::fromCallable([$this, 'Check']));
		}

		private function OutHead(): void {
			Layout::instance()->header->Push("<div>Привет, " . USER_LOGIN . "</div>");
			Layout::instance()->header->Push(Actions\Users::$exit->GetLinkHref('', [], ['class' => 'logout']));
		}

		private function OutMenu() {
			Layout::instance()->menu->Push(TPL\Item::ToVar('<a href = "' . self::$site->GetAddress() . '" target = "_blank">Открыть сайт</a>'));
			Layout::instance()->menu->Push(TPL\Item::ToVar(self::$home->GetLinkHref('Главная')));
			Layout::instance()->menu->Push(
				TPL\Group::ToVar('База данных', [
					self::$db_structure->GetLinkHref('Структура'),
					self::$db_check->GetLinkHref('Проверить')
				])
			);
			Composition::instance()->OutMenu();
			Statistics::instance()->OutMenu();
			News::instance()->OutMenu();
			Changes::instance()->OutMenu();
			Feedback::instance()->OutMenu();
		}

		private function OutFooter() {
			Layout::instance()->footer->Push('© ' . Params::$site_name);
		}

		private function Structure() {
			Layout::instance()->main->Push(TPL\Structure::ToVar($this->model->Structure()));
		}

		private function Home() {
			Layout::instance()->main->Push($this->model->Home());
		}

		private function Check() {
			$result = json_encode($this->model->DBCheck());
			Layout::instance()->js_loaded->Push(/** @lang JavaScript */ "Admin.General.Render.CheckDB({$result});");
		}

	}

	General::init();