<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'general/admin/general.actions.inc';
	require DIR_UNITS . 'general/admin/general.model.inc';

	require DIR_UNITS . 'general/admin/views/group.tpl';
	require DIR_UNITS . 'general/admin/views/structure.tpl';
	require DIR_UNITS . 'general/admin/views/check.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Helper\Response;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General AS TPL;
	use Proj\Params;
	use Closure;

	class General extends Actions\General {
		use Instance;

		private Model\General $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\General::instance();

			self::$view->Push([self::ENTRY_HTML], self::$out_head, Closure::fromCallable([$this, 'OutHead']));
			self::$view->Push([self::ENTRY_HTML], self::$out_menu, Closure::fromCallable([$this, 'OutMenu']));
			self::$view->Push([self::ENTRY_HTML], self::$out_footer, Closure::fromCallable([$this, 'OutFooter']));

			self::$view->Push([self::ENTRY_XHR], self::$home, Closure::fromCallable([$this, 'Home']));
			self::$view->Push([self::ENTRY_XHR], self::$db_structure, Closure::fromCallable([$this, 'Structure']));
			self::$view->Push([self::ENTRY_XHR], self::$db_check, Closure::fromCallable([$this, 'Check']));
			self::$view->Push([self::ENTRY_XHR], self::$db_make, Closure::fromCallable([$this, 'Make']));
		}

		#region HTML

		private function OutHead(): void {
			Layout::instance()->header->Push("<div>Привет, " . Model\Users::instance()->GetAlias() . "</div>");
			Layout::instance()->header->Push(Actions\Users::$exit->GetLinkHref('', [], ['class' => 'logout']));
		}

		private function OutMenu() {
			Layout::instance()->menu->Push(TPL\Item::ToVar('<a href = "' . self::$site->GetAddress() . '" target = "_blank">Открыть сайт</a>'));

			Layout::instance()->menu->Push($this->OutMenuSeparator());
			Layout::instance()->menu->Push(TPL\Item::ToVar(self::$home->GetLinkHref('Главная')));

			$menuBD = [];
			if ($this->Allow(self::ACCESS_DB_STRUCTURE)) $menuBD[] = self::$db_structure->GetLinkHref('Структура');
			if ($this->Allow(self::ACCESS_DB_CHECK)) $menuBD[] = self::$db_check->GetLinkHref('Проверить');
			$menuComposition = Composition::instance()->GetMenu();
			$menuStatistics = Statistics::instance()->GetMenu();
			if ($menuBD || $menuComposition || $menuStatistics) {
				Layout::instance()->menu->Push($this->OutMenuSeparator());
				Layout::instance()->menu->Push($this->OutMenuHead('Разработка'));
				if ($menuBD) Layout::instance()->menu->Push(TPL\Group::ToVar('База данных', $menuBD));
				if ($menuComposition) Layout::instance()->menu->Push(TPL\Group::ToVar('Композиция', $menuComposition));
				if ($menuStatistics) Layout::instance()->menu->Push(TPL\Group::ToVar('Статистика', $menuStatistics));
			}

			$menuGroup = Users::instance()->GetMenuGroup();
			$menuUser = Users::instance()->GetMenuUser();
			if ($menuGroup || $menuUser) {
				Layout::instance()->menu->Push($this->OutMenuSeparator());
				Layout::instance()->menu->Push($this->OutMenuHead('Безопасность'));
				if ($menuGroup) Layout::instance()->menu->Push(TPL\Group::ToVar('Группы', $menuGroup));
				if ($menuUser) Layout::instance()->menu->Push(TPL\Group::ToVar('Пользователи', $menuUser));
			}

			$menuNews = News::instance()->GetMenu();
			$menuChanges = Changes::instance()->GetMenu();
			$menuFeedback = Feedback::instance()->GetMenu();
			if ($menuNews || $menuChanges) {
				Layout::instance()->menu->Push($this->OutMenuSeparator());
				Layout::instance()->menu->Push($this->OutMenuHead('Сайт'));
				if ($menuNews) Layout::instance()->menu->Push(TPL\Group::ToVar('Новости', $menuNews));
				if ($menuChanges) Layout::instance()->menu->Push(TPL\Group::ToVar('Актуальное', $menuChanges));
				if ($menuFeedback) Layout::instance()->menu->Push(TPL\Group::ToVar('Обратная связь', $menuFeedback));
			}
		}

		#endregion HTML

		private function OutMenuSeparator(): string {
			return '<hr>';
		}

		private function OutMenuHead(string $text): string {
			return "<div class = 'head'>{$text}</div>";
		}

		private function OutFooter() {
			Layout::instance()->footer->Push('© ' . Params::$site_name);
		}

		#region XHR

		#[NoReturn] private function Home() {
			Response::PushHistory(self::$home);
			Response::PushSection('main', $this->model->Home());
			Response::SendJSON();
		}

		#[NoReturn] private function Structure() {
			if (!$this->Allow(self::ACCESS_DB_STRUCTURE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushHistory(self::$db_structure);
			Response::PushSection('main', TPL\Structure::ToVar($this->model->Structure()));
			Response::SendJSON();
		}

		#[NoReturn] private function Check() {
			if (!$this->Allow(self::ACCESS_DB_CHECK)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushHistory(self::$db_check);
			Response::PushSection('main', TPL\Check::ToVar($this->model->DBCheck()));
			Response::SendJSON();
		}

		#[NoReturn] private function Make() {
			if (!$this->Allow(self::ACCESS_DB_MAKE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushData($this->model->DBMake());
			Response::SendJSON();
		}

		#endregion XHR

	}

	General::init();