<?php

	namespace Proj\Admin\Editor\Model;

	use Base\Editor\Skins\Browse;
	use Base\Editor\Skins\Edit;
	use Proj\Units\Consts;

	trait News {

		private function Init(): void {
			$this->titleSelect = 'Список новостей';
			$this->titleBrowse = 'Просмотр новости';
			$this->titleCreate = 'Добавление новости';
			$this->titleUpdate = 'Редактирование новости';
			$this->titleDelete = 'Удалить новость?';

			$this->querySelect->where('`state` != '. Consts\News::STATES['delete'])->order('datecr', 'DESC')->order('id', 'DESC');
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

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\News::PATH_COVER;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

		private function DeleteCover($id): void {
			$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
			if ($old_file) unlink(Consts\News::PATH_COVER . $old_file);
		}

	}