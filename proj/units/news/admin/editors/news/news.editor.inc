<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'news/admin/editors/news/news.editor.model.inc';

	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Editor\Skins\Browse;
	use Base\Editor\Skins\Edit;
	use Proj\Admin\Editor\Model;
	use Proj\Units\Consts;

	class News extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список новостей';
			$this->titleBrowse = 'Просмотр новости';
			$this->titleCreate = 'Добавление новости';
			$this->titleUpdate = 'Редактирование новости';
			$this->titleDelete = 'Удалить новость?';

			$this->titleDoCreate = 'Новость добавлена';
			$this->titleDoUpdate = 'Новость изменена';
			$this->titleDoDelete = 'Новость удалена';

			$this->model = new Model\News($table, $this->params);
		}

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Browse\Text('#'),
				'state' 	=> new Browse\ValueFromArray('Состояние', Consts\News::STATES_VIEW),
				'datepb'	=> new Browse\DateFormat('Дата публикации', 'd.m.Y H:i'),
				'header' 	=> new Browse\Text('Заголовок')
			];
		}

		protected function FieldsBrowse(): array {
			return [
				'state'		=> new Browse\ValueFromArray('Состояние', Consts\News::STATES_VIEW),
				'header'	=> new Browse\Text('Заголовок'),
				'content'	=> new Browse\Text('Текст'),
				'datepb'	=> new Browse\DateFormat('Дата публикации', 'd.m.Y H:i')
			];
		}

		protected function FieldsCreate(): array {
			return [
				'state'		=> new Edit\Hidden('Состояние', 'form[state]', Consts\News::STATES['draft']),
				'header'	=> new Edit\Text('Заголовок', 'form[header]'),
				'content'	=> new Edit\TextArea('Текст', 'form[content]'),
				'cover'		=> new Edit\File('Обложка', 'form[cover]', 'Выберите обложку', '.jpg, .jpeg, .png'),
				'datepb'	=> new Edit\DateTime('Дата публикации', 'form[datepb]')
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'state'		=> new Edit\Select('Состояние', 'form[state]', [
					Consts\News::STATE_DRAFT	=> 'Черновик',
					Consts\News::STATE_ACTIVE	=> 'Активная',
					Consts\News::STATE_INACTIVE	=> 'Не активная',
				]),
				'header'	=> new Edit\Text('Заголовок', 'form[header]'),
				'content'	=> new Edit\TextArea('Текст', 'form[content]'),
				'cover'		=> new Edit\File('Обложка', 'form[cover]', 'Выберите обложку', '.jpg, .jpeg, .png'),
				'datepb'	=> new Edit\DateTime('Дата публикации', 'form[datepb]')
			];
		}

	}