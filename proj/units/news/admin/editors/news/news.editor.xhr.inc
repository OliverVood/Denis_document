<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'news/admin/editors/news/news.editor.model.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\EditorMySQLi\XHR\Editor;;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;
	use Response;

	class News extends Editor {
		use Model\News;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();

			$this->titleDoCreate = 'Новость добавлена';
			$this->titleDoUpdate = 'Новость изменена';
			$this->titleDoDelete = 'Новость удалена';
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			Response::PushNoticeOk($this->titleDoCreate);
			$this->OnSelect();
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = GetInt('id');
			$data = GetParam('form', []);

			if ($_FILES['form']['tmp_name']['cover']) {
				$this->DeleteCover($id);
				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			Response::PushNoticeOk($this->titleDoUpdate);
			$this->OnSelect();
		}

	}