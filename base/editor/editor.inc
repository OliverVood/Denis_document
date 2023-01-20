<?php

	namespace Base;

	require 'views/select.tpl';
	require 'views/create.tpl';
	require 'views/update.tpl';

	use Base\DB\Table;
	use JetBrains\PhpStorm\NoReturn;

	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Update;

	class Editor {
		protected string $name;
		protected array $params;
		protected Table $table;

		public Action $select;
		public Action $create;
		public Action $update;

		protected string $titleSelect;

		protected function __construct(string $name, Table $table, array $params = []) {
			$this->name = $name;
			$this->params = $params;
			$this->table = $table;

			$this->titleSelect = $this->params['titles']['select'] ?? 'Выборка';
			$this->titleSelect = $this->params['titles']['create'] ?? 'Создание';
			$this->titleSelect = $this->params['titles']['update'] ?? 'Редактирование';
			$this->titleSelect = $this->params['titles']['view'] ?? 'Просмотр';

			$this->select = new Action($this->name, 'select', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/select', Admin.General.Render.ToMain); return false;");
			$this->create = new Action($this->name, 'create', 'default');
			$this->update = new Action($this->name, 'update', 'default');

			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);
		}

		#[NoReturn] public function OnSelect(): void {
			$order = isset($this->params['order']) ? implode(', ', $this->params['order']) : null;

			$result = $this->table->Select(null, null, $order);
			$items = $this->table->FetchAll($result, function(& $items, $item) {
				$items[] = $item;
			});

			SendJSONSuccess(['html' => Select::object()->ToVar($this->params['select'] ?? [], $items, $this->titleSelect)]);
		}

		public function OnCreate() : void {
			Create::object()->ToVar();
		}

		public function OnUpdate() : void {
			Update::object()->ToVar();
		}

	}