<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'changes/admin/editors/change/change.editor.model.inc';

	use Base\ActionRight;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins\Browse;
	use Base\Editor\Skins\Edit;
	use Proj\Units\Consts;
	use Proj\Admin\Editor\Model;

	class Change extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->params['cid'] = GetInt('cid');

			$this->titleSelect = 'Список актуального';
			$this->titleCreate = 'Добавить актуальное';
			$this->titleUpdate = 'Редактировать актуальное';
			$this->titleDelete = 'Удалить актуальное?';

			$this->titleDoCreate = 'Актуальное добавлено';
			$this->titleDoUpdate = 'Актуальное изменено';
			$this->titleDoDelete = 'Актуальное удалено';

			$this->model = new Model\Change($table, $this->params);
	}

		protected function RegActionSelect(): void { $this->select = new ActionRight($this->id, $this->name, 'select', "/{$this->name}/select?cid=%cid%&page=%page%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/select', {cid: %cid%, page: %page%}); return false;"); }
		protected function RegActionCreate(): void { $this->create = new ActionRight($this->id, $this->name, 'create', "/{$this->name}/create?cid=%cid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/create', {cid: %cid%}); return false;"); }
		protected function RegActionUpdate(): void { $this->update = new ActionRight($this->id, $this->name, 'update', "/{$this->name}/update?id=%id%&cid=%cid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/update', {id: %id%, cid: %cid%}); return false;"); }

		protected function RegActionDoDelete(): void { $this->do_delete = new ActionRight($this->id, $this->name, 'do_delete', "/{$this->name}/do_delete?id=%id%&cid=%cid%", /* @lang JavaScript */ "if (confirm('{$this->titleDelete}')) Base.Common.Query.SendData('/{$this->name}/do_delete', {id: %id%, cid: %cid%}); return false;"); }

		protected function NavigateSelect(): array { return [ function () { return $this->create->GetLinkHrefAllow(self::ACCESS_SELECT, $this->titleCreate, array_merge(['page' => 1], $this->params)); } ]; }

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHrefAllow(self::ACCESS_UPDATE, 'Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHrefAllow(self::ACCESS_DELETE, 'Удалить', array_merge(['id' => $item['id']], $this->params)); }
			];
		}

		protected function FieldsSelect(): array {
			return [
				'id'			=> new Browse\Text('#'),
				'state'			=> new Browse\ValueFromArray('Состояние', Consts\Changes::STATES_VIEW),
				'header'		=> new Browse\Text('Заголовок'),
			];
		}

		protected function FieldsCreate(): array {
			return [
				'cid'			=> new Edit\Hidden('Список актуального', 'form[cid]', $this->params['cid']),
				'state'			=> new Edit\Hidden('Состояние', 'form[state]', Consts\Changes::STATES['draft']),
				'header'		=> new Edit\Text('Заголовок', 'form[header]'),
				'content'		=> new Edit\TextArea('Текст', 'form[content]'),
				'cover'			=> new Edit\File('Обложка', 'form[cover]', 'Выберите обложку', '.jpg, .jpeg, .png')
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'state'			=> new Edit\Select('Состояние', 'form[state]', [
					Consts\Changes::STATE_DRAFT	=> 'Черновик',
					Consts\Changes::STATE_ACTIVE	=> 'Активный',
					Consts\Changes::STATE_INACTIVE	=> 'Не активный',
				]),
				'header'		=> new Edit\Text('Заголовок', 'form[header]'),
				'content'		=> new Edit\TextArea('Текст', 'form[content]'),
				'cover'			=> new Edit\File('Обложка', 'form[cover]', 'Выберите обложку', '.jpg, .jpeg, .png')
			];
		}

	}