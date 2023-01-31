<?php

	namespace Proj\Admin\Units;

	require 'opportunities.structure.inc';
	require 'opportunities.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Editor\EditorMySQLi;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Opportunities extends Structure\Opportunities {
		use Instance;

		private EditorMySQLi $editor_opportunities;

		private Action $out_menu;


		private function __construct() {
			parent::__construct();

			$this->editor_opportunities = new \Proj\Admin\Editor\Opportunities(self::NAME, $this->table_opportunities);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::object()->ToVar('Новые возможности', [
					$this->editor_opportunities->select->GetLink('Список новых возможностей'),
					$this->editor_opportunities->create->GetLink('Добавить новые возможности')
				])
			);
		}

	}

	Opportunities::init();