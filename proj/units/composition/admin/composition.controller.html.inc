<?php

	namespace Proj\Admin\Units\HTML;

	require DIR_UNITS . 'composition/admin/composition.actions.inc';
	require DIR_UNITS . 'composition/admin/views/units.tpl';
	require DIR_UNITS . 'composition/admin/views/models.tpl';
	require DIR_UNITS . 'composition/admin/views/editors.tpl';

	use Base\Units;
	use Base\Editor;
	use Base\Instance;
	use Proj\Admin\Actions;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates AS TPLS;
	use Closure;

	class Composition extends Actions\Composition {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);

			self::$view->Push(self::$new_unit, Closure::fromCallable([$this, 'NewUnit']));
			self::$view->Push(self::$new_model, Closure::fromCallable([$this, 'NewModel']));
			self::$view->Push(self::$new_editor, Closure::fromCallable([$this, 'NewEditor']));
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				TPLS\General\Group::ToVar('Композиция', [
					self::$new_unit->GetLinkHref('Добавить единицу'),
					self::$new_model->GetLinkHref('Добавить модель'),
					self::$new_editor->GetLinkHref('Добавить редактор')
				])
			);
		}

		private function NewUnit() {
			Layout::instance()->main->Push(TPLS\Composition\Units::ToVar(Units::GetUnitList()));
		}

		private function NewModel() {
			Layout::instance()->main->Push(TPLS\Composition\Models::ToVar(Units::GetUnitList(), self::ROUTES));
		}

		private function NewEditor() {
			Layout::instance()->main->Push(TPLS\Composition\Editors::ToVar(Editor\Basic::GetEditorList(), Units::GetUnitList()));
		}

	}

	Composition::init();